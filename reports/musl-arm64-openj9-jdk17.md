---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-05 09:56:10 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 9.85/sec |
| Health Score | 616% |
| Threads | 11 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1793890187 43
1793890192 43
1793890197 43
1793890202 43
1793890207 43
1793890212 43
1793890217 43
1793890222 43
1793890227 43
1793890232 48
1793890237 48
1793890242 48
1793890247 48
1793890252 48
1793890257 48
1793890262 47
1793890267 47
1793890272 47
1793890277 47
1793890282 47
```
</details>

---

