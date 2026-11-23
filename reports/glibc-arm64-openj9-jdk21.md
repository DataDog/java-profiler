---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 07:20:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 9 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 7 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (2 unique values: 44-64 cores)</summary>

```
1795436154 44
1795436159 44
1795436164 44
1795436169 64
1795436174 64
1795436179 64
1795436184 64
1795436189 64
1795436194 64
1795436199 64
1795436204 64
1795436209 64
1795436214 64
1795436219 64
1795436224 64
1795436229 64
1795436234 64
1795436239 64
1795436244 64
1795436249 64
```
</details>

---

