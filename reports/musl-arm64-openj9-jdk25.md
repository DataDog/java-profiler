---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 08:53:22 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 11 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (2 unique values: 38-48 cores)</summary>

```
1794318496 48
1794318501 48
1794318506 48
1794318511 48
1794318516 48
1794318521 48
1794318526 48
1794318531 48
1794318536 48
1794318541 48
1794318546 48
1794318551 48
1794318556 48
1794318561 48
1794318566 48
1794318571 48
1794318576 48
1794318581 38
1794318586 38
1794318591 38
```
</details>

---

