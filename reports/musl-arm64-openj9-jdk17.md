---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 05:21:38 EST

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
| CPU Cores (start) | 36 |
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
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 330 |
| Sample Rate | 5.50/sec |
| Health Score | 344% |
| Threads | 11 |
| Allocations | 137 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1794824121 36
1794824126 36
1794824131 36
1794824136 36
1794824141 36
1794824146 36
1794824151 36
1794824156 36
1794824161 36
1794824166 36
1794824171 36
1794824176 36
1794824181 36
1794824186 48
1794824191 48
1794824196 48
1794824201 48
1794824206 48
1794824211 48
1794824216 48
```
</details>

---

