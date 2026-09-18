---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 07:44:21 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 37 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 11 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1789731605 47
1789731610 47
1789731615 47
1789731620 47
1789731625 47
1789731630 47
1789731635 47
1789731640 47
1789731645 47
1789731650 47
1789731655 47
1789731660 48
1789731665 48
1789731670 48
1789731675 48
1789731680 48
1789731685 48
1789731690 48
1789731695 48
1789731700 48
```
</details>

---

