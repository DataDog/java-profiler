---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-25 11:54:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 654 |
| Sample Rate | 10.90/sec |
| Health Score | 681% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 10 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (2 unique values: 24-32 cores)</summary>

```
1787672972 32
1787672977 32
1787672982 32
1787672987 32
1787672992 32
1787672997 32
1787673002 32
1787673007 24
1787673012 24
1787673017 24
1787673022 24
1787673027 24
1787673032 24
1787673037 24
1787673042 24
1787673047 24
1787673052 24
1787673057 24
1787673062 24
1787673067 24
```
</details>

---

