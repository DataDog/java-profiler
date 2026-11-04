---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-04 05:58:33 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 9 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793789560 48
1793789565 48
1793789570 48
1793789575 48
1793789580 48
1793789585 48
1793789590 48
1793789595 48
1793789600 48
1793789605 48
1793789610 43
1793789615 43
1793789620 43
1793789625 43
1793789630 43
1793789635 43
1793789640 43
1793789645 43
1793789650 43
1793789655 43
```
</details>

---

