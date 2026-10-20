---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-20 12:29:08 EDT

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
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 237 |
| Sample Rate | 3.95/sec |
| Health Score | 247% |
| Threads | 10 |
| Allocations | 142 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 119 |
| Sample Rate | 1.98/sec |
| Health Score | 124% |
| Threads | 10 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (3 unique values: 41-52 cores)</summary>

```
1792513474 42
1792513479 42
1792513484 42
1792513489 42
1792513494 42
1792513499 42
1792513504 42
1792513509 42
1792513514 42
1792513519 42
1792513524 42
1792513529 42
1792513534 42
1792513539 42
1792513545 42
1792513550 52
1792513555 52
1792513560 52
1792513565 52
1792513570 52
```
</details>

---

