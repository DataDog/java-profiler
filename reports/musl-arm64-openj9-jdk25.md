---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-19 15:50:36 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 9 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (7 unique values: 42-57 cores)</summary>

```
1795121177 42
1795121182 47
1795121187 47
1795121192 47
1795121197 47
1795121202 50
1795121207 50
1795121212 51
1795121217 51
1795121222 51
1795121227 51
1795121232 51
1795121237 51
1795121242 51
1795121247 51
1795121252 54
1795121257 54
1795121262 54
1795121267 52
1795121272 52
```
</details>

---

