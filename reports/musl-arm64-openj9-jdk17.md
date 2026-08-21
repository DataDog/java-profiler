---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-21 09:26:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 259 |
| Sample Rate | 4.32/sec |
| Health Score | 270% |
| Threads | 10 |
| Allocations | 131 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 14 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (3 unique values: 29-34 cores)</summary>

```
1787318501 34
1787318506 33
1787318511 33
1787318516 33
1787318521 33
1787318526 33
1787318531 33
1787318536 34
1787318541 34
1787318546 34
1787318551 34
1787318556 34
1787318561 34
1787318566 34
1787318571 34
1787318576 34
1787318581 34
1787318586 34
1787318591 34
1787318596 29
```
</details>

---

