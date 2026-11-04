---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-04 17:02:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 677 |
| Sample Rate | 11.28/sec |
| Health Score | 705% |
| Threads | 11 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (1 unique values: 43-43 cores)</summary>

```
1793829556 43
1793829561 43
1793829566 43
1793829571 43
1793829576 43
1793829581 43
1793829586 43
1793829591 43
1793829596 43
1793829601 43
1793829606 43
1793829611 43
1793829616 43
1793829621 43
1793829626 43
1793829631 43
1793829636 43
1793829641 43
1793829646 43
1793829651 43
```
</details>

---

