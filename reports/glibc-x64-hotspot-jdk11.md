---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 14:53:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 11 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 7 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (4 unique values: 71-79 cores)</summary>

```
1795636155 74
1795636160 74
1795636165 74
1795636170 74
1795636175 74
1795636180 74
1795636185 74
1795636190 74
1795636195 74
1795636200 74
1795636205 74
1795636210 74
1795636215 79
1795636220 79
1795636225 79
1795636230 79
1795636235 79
1795636240 79
1795636245 79
1795636250 76
```
</details>

---

