---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 13:35:20 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 9 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 13 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (4 unique values: 38-47 cores)</summary>

```
1794508140 43
1794508145 43
1794508150 43
1794508155 43
1794508160 43
1794508165 43
1794508170 43
1794508175 43
1794508180 38
1794508185 38
1794508190 38
1794508195 38
1794508200 38
1794508205 38
1794508210 38
1794508215 38
1794508220 38
1794508225 38
1794508230 38
1794508235 38
```
</details>

---

