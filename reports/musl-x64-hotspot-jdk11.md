---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-23 10:56:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 10 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 761 |
| Sample Rate | 12.68/sec |
| Health Score | 792% |
| Threads | 9 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (4 unique values: 74-93 cores)</summary>

```
1792767111 74
1792767116 74
1792767121 74
1792767126 74
1792767131 74
1792767136 74
1792767141 74
1792767146 74
1792767151 74
1792767156 74
1792767161 89
1792767166 89
1792767171 89
1792767176 89
1792767181 89
1792767186 91
1792767191 91
1792767196 91
1792767201 91
1792767206 91
```
</details>

---

