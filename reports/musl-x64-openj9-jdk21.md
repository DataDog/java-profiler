---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-10 19:36:46 EST

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 719 |
| Sample Rate | 11.98/sec |
| Health Score | 749% |
| Threads | 9 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (6 unique values: 18-29 cores)</summary>

```
1794357141 27
1794357146 27
1794357151 27
1794357156 27
1794357161 27
1794357166 27
1794357171 29
1794357176 29
1794357181 29
1794357186 20
1794357191 20
1794357196 20
1794357201 20
1794357206 20
1794357211 20
1794357216 18
1794357221 18
1794357226 20
1794357231 20
1794357236 21
```
</details>

---

