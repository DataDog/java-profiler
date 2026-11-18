---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 09:52:45 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 13 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (2 unique values: 36-38 cores)</summary>

```
1795013156 38
1795013161 38
1795013166 38
1795013171 38
1795013176 38
1795013181 38
1795013186 38
1795013192 38
1795013197 38
1795013202 38
1795013207 38
1795013212 38
1795013217 38
1795013222 38
1795013227 38
1795013232 38
1795013237 36
1795013242 36
1795013247 36
1795013252 36
```
</details>

---

