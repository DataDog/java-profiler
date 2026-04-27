---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-27 03:38:45 EDT

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 9 |
| Allocations | 45 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 286 |
| Sample Rate | 4.77/sec |
| Health Score | 298% |
| Threads | 10 |
| Allocations | 135 |

<details>
<summary>CPU Timeline (2 unique values: 54-59 cores)</summary>

```
1777275298 54
1777275303 54
1777275308 54
1777275313 54
1777275318 59
1777275323 59
1777275328 59
1777275333 59
1777275338 59
1777275343 59
1777275348 59
1777275353 59
1777275358 59
1777275363 59
1777275368 59
1777275373 59
1777275378 59
1777275383 59
1777275388 59
1777275393 59
```
</details>

---

