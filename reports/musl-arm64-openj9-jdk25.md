---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-25 11:54:20 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 266 |
| Sample Rate | 4.43/sec |
| Health Score | 277% |
| Threads | 11 |
| Allocations | 156 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 11 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1787672947 64
1787672952 64
1787672957 64
1787672962 64
1787672967 64
1787672972 64
1787672977 64
1787672982 64
1787672987 64
1787672992 64
1787672997 64
1787673002 64
1787673007 64
1787673012 64
1787673017 59
1787673022 59
1787673027 59
1787673032 59
1787673037 59
1787673042 59
```
</details>

---

