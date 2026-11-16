---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-15 20:26:56 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 9 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 255 |
| Sample Rate | 4.25/sec |
| Health Score | 266% |
| Threads | 14 |
| Allocations | 152 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1794792177 48
1794792182 48
1794792187 48
1794792192 48
1794792197 48
1794792202 48
1794792207 48
1794792212 48
1794792217 48
1794792222 48
1794792227 48
1794792232 48
1794792237 48
1794792242 48
1794792247 48
1794792252 48
1794792257 48
1794792262 48
1794792267 48
1794792272 48
```
</details>

---

