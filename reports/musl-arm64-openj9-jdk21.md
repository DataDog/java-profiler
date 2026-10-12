---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-11 23:08:38 EDT

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
| CPU Cores (start) | 16 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 9 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 9 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (1 unique values: 16-16 cores)</summary>

```
1791774129 16
1791774134 16
1791774139 16
1791774144 16
1791774149 16
1791774154 16
1791774159 16
1791774164 16
1791774169 16
1791774174 16
1791774179 16
1791774184 16
1791774189 16
1791774194 16
1791774199 16
1791774204 16
1791774209 16
1791774214 16
1791774219 16
1791774224 16
```
</details>

---

