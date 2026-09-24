---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-24 05:51:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 960 |
| Sample Rate | 16.00/sec |
| Health Score | 1000% |
| Threads | 10 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1031 |
| Sample Rate | 17.18/sec |
| Health Score | 1074% |
| Threads | 10 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (2 unique values: 62-63 cores)</summary>

```
1790243119 63
1790243124 63
1790243129 63
1790243134 63
1790243139 63
1790243144 63
1790243150 63
1790243155 63
1790243160 63
1790243165 63
1790243170 63
1790243175 63
1790243180 63
1790243185 63
1790243190 63
1790243195 63
1790243200 62
1790243205 62
1790243210 62
1790243215 62
```
</details>

---

