---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-02 14:28:39 EST

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
| CPU Cores (start) | 15 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 663 |
| Sample Rate | 11.05/sec |
| Health Score | 691% |
| Threads | 9 |
| Allocations | 426 |

<details>
<summary>CPU Timeline (3 unique values: 12-32 cores)</summary>

```
1793647477 15
1793647482 15
1793647487 15
1793647492 15
1793647497 15
1793647502 15
1793647507 15
1793647512 15
1793647517 32
1793647522 32
1793647527 32
1793647532 32
1793647537 12
1793647542 12
1793647547 12
1793647552 12
1793647557 12
1793647562 12
1793647567 12
1793647572 12
```
</details>

---

