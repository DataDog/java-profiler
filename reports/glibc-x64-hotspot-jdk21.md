---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-11 10:31:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 10 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 759 |
| Sample Rate | 12.65/sec |
| Health Score | 791% |
| Threads | 11 |
| Allocations | 429 |

<details>
<summary>CPU Timeline (4 unique values: 50-57 cores)</summary>

```
1778509482 54
1778509487 54
1778509492 54
1778509497 54
1778509502 57
1778509507 57
1778509512 57
1778509517 57
1778509522 57
1778509527 57
1778509532 57
1778509537 57
1778509542 57
1778509547 57
1778509552 57
1778509557 57
1778509562 57
1778509567 57
1778509572 57
1778509577 57
```
</details>

---

