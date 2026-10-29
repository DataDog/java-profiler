---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-29 13:19:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 9 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (2 unique values: 38-40 cores)</summary>

```
1793293977 40
1793293982 40
1793293987 40
1793293992 40
1793293997 40
1793294002 40
1793294007 40
1793294012 40
1793294017 40
1793294022 40
1793294027 40
1793294032 40
1793294037 40
1793294042 40
1793294047 40
1793294052 40
1793294057 40
1793294062 40
1793294067 38
1793294072 38
```
</details>

---

