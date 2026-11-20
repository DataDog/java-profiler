---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-20 09:53:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 9 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (5 unique values: 41-46 cores)</summary>

```
1795186131 41
1795186136 41
1795186141 41
1795186146 41
1795186151 44
1795186156 44
1795186161 44
1795186166 45
1795186171 45
1795186176 45
1795186181 45
1795186186 45
1795186191 45
1795186196 43
1795186201 43
1795186206 46
1795186211 46
1795186216 46
1795186221 46
1795186226 45
```
</details>

---

