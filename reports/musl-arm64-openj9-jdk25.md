---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-02 08:00:03 EST

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 394 |
| Sample Rate | 6.57/sec |
| Health Score | 411% |
| Threads | 8 |
| Allocations | 424 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 13 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (2 unique values: 19-20 cores)</summary>

```
1793624147 20
1793624152 20
1793624157 20
1793624162 20
1793624167 20
1793624172 20
1793624177 20
1793624182 20
1793624187 20
1793624192 20
1793624197 20
1793624202 20
1793624207 19
1793624212 19
1793624217 19
1793624222 19
1793624227 19
1793624232 19
1793624237 19
1793624242 19
```
</details>

---

