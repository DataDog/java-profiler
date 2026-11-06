---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-05 19:52:40 EST

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
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 8 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (3 unique values: 14-21 cores)</summary>

```
1793926094 16
1793926099 21
1793926104 21
1793926109 21
1793926114 21
1793926119 21
1793926124 21
1793926129 21
1793926134 21
1793926139 21
1793926144 21
1793926149 16
1793926154 16
1793926159 16
1793926164 16
1793926169 16
1793926174 16
1793926179 16
1793926184 16
1793926189 14
```
</details>

---

