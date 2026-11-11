---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 19:36:46 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 256 |
| Sample Rate | 4.27/sec |
| Health Score | 267% |
| Threads | 16 |
| Allocations | 137 |

<details>
<summary>CPU Timeline (2 unique values: 47-60 cores)</summary>

```
1794357134 47
1794357139 47
1794357144 47
1794357149 47
1794357154 47
1794357159 47
1794357164 47
1794357169 47
1794357174 47
1794357179 47
1794357184 47
1794357189 60
1794357194 60
1794357199 60
1794357204 60
1794357209 60
1794357214 60
1794357219 60
1794357224 60
1794357229 60
```
</details>

---

