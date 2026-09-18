---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 11:05:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 239 |
| Sample Rate | 3.98/sec |
| Health Score | 249% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 427 |
| Sample Rate | 7.12/sec |
| Health Score | 445% |
| Threads | 10 |
| Allocations | 143 |

<details>
<summary>CPU Timeline (3 unique values: 42-47 cores)</summary>

```
1789743496 42
1789743501 42
1789743506 42
1789743511 42
1789743516 42
1789743521 42
1789743526 42
1789743531 42
1789743536 45
1789743541 45
1789743546 45
1789743551 45
1789743556 45
1789743561 45
1789743566 45
1789743571 45
1789743576 45
1789743581 45
1789743586 47
1789743591 47
```
</details>

---

