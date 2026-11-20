---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-20 06:08:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 7 |
| Allocations | 87 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 8 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (3 unique values: 24-34 cores)</summary>

```
1795172551 34
1795172556 34
1795172561 34
1795172566 34
1795172571 34
1795172576 34
1795172581 34
1795172586 34
1795172591 34
1795172596 34
1795172601 34
1795172606 34
1795172611 34
1795172616 34
1795172621 34
1795172626 29
1795172632 29
1795172637 29
1795172642 29
1795172647 29
```
</details>

---

