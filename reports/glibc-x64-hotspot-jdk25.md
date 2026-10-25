---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-25 08:54:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 398 |
| Sample Rate | 6.63/sec |
| Health Score | 414% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1792932536 30
1792932541 30
1792932546 30
1792932551 30
1792932556 30
1792932561 30
1792932566 30
1792932571 30
1792932576 30
1792932581 30
1792932586 30
1792932591 30
1792932596 28
1792932601 28
1792932606 28
1792932611 28
1792932616 28
1792932621 28
1792932626 28
1792932631 28
```
</details>

---

