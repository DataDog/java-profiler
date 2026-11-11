---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-11 17:16:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 600 |
| Sample Rate | 10.00/sec |
| Health Score | 625% |
| Threads | 9 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 771 |
| Sample Rate | 12.85/sec |
| Health Score | 803% |
| Threads | 11 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (4 unique values: 77-84 cores)</summary>

```
1794435111 77
1794435116 77
1794435121 77
1794435126 77
1794435131 79
1794435136 79
1794435141 79
1794435146 79
1794435151 79
1794435156 81
1794435161 81
1794435166 84
1794435171 84
1794435176 84
1794435181 84
1794435187 84
1794435192 84
1794435197 84
1794435202 84
1794435207 84
```
</details>

---

