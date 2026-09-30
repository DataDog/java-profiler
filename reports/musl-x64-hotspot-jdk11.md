---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-30 12:30:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 888 |
| Sample Rate | 14.80/sec |
| Health Score | 925% |
| Threads | 9 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (2 unique values: 29-30 cores)</summary>

```
1790785536 30
1790785541 30
1790785546 30
1790785551 30
1790785556 30
1790785561 30
1790785566 29
1790785571 29
1790785576 29
1790785581 29
1790785586 29
1790785591 29
1790785596 29
1790785601 29
1790785606 29
1790785611 29
1790785616 29
1790785621 29
1790785626 29
1790785631 29
```
</details>

---

