---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 06:36:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 10 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 11 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (3 unique values: 63-85 cores)</summary>

```
1795001500 76
1795001505 76
1795001510 76
1795001515 76
1795001520 76
1795001525 76
1795001530 76
1795001535 76
1795001540 76
1795001545 76
1795001550 85
1795001555 85
1795001560 63
1795001565 63
1795001570 63
1795001575 63
1795001580 63
1795001585 63
1795001590 63
1795001595 63
```
</details>

---

