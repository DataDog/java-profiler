---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ❌ FAIL

**Date:** 2026-11-18 14:19:57 EST

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
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 13 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (1 unique values: 38-38 cores)</summary>

```
1795029372 38
1795029377 38
1795029382 38
1795029387 38
1795029392 38
1795029397 38
1795029402 38
1795029407 38
1795029412 38
1795029417 38
1795029422 38
1795029427 38
1795029432 38
1795029437 38
1795029442 38
1795029447 38
1795029452 38
1795029457 38
1795029462 38
1795029467 38
```
</details>

---

