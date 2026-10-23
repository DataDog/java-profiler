---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-23 10:30:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 7 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 11 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (3 unique values: 37-40 cores)</summary>

```
1792765530 37
1792765535 37
1792765540 37
1792765545 40
1792765551 40
1792765556 40
1792765561 40
1792765566 38
1792765571 38
1792765576 38
1792765581 38
1792765586 38
1792765591 38
1792765596 38
1792765601 38
1792765606 38
1792765611 38
1792765616 38
1792765621 38
1792765626 38
```
</details>

---

