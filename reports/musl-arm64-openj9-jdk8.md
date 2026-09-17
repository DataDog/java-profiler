---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-17 15:41:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 158 |
| Sample Rate | 2.63/sec |
| Health Score | 164% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 145 |
| Sample Rate | 2.42/sec |
| Health Score | 151% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 28-33 cores)</summary>

```
1789673511 33
1789673516 33
1789673521 33
1789673526 33
1789673531 33
1789673536 33
1789673541 33
1789673546 33
1789673551 33
1789673556 33
1789673561 33
1789673566 33
1789673571 33
1789673577 33
1789673582 33
1789673587 33
1789673592 33
1789673597 28
1789673602 28
1789673607 28
```
</details>

---

