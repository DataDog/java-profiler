---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-30 10:12:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 9 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 14 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (4 unique values: 42-54 cores)</summary>

```
1777558150 42
1777558155 42
1777558160 44
1777558165 44
1777558170 44
1777558175 44
1777558180 44
1777558185 44
1777558190 49
1777558195 49
1777558200 54
1777558205 54
1777558210 54
1777558215 54
1777558220 54
1777558225 54
1777558230 54
1777558235 54
1777558240 54
1777558245 54
```
</details>

---

