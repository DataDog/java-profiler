---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-17 08:01:55 EST

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 870 |
| Sample Rate | 14.50/sec |
| Health Score | 906% |
| Threads | 10 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (3 unique values: 71-79 cores)</summary>

```
1794920149 77
1794920154 77
1794920159 77
1794920164 77
1794920169 77
1794920174 77
1794920179 77
1794920184 77
1794920189 77
1794920194 79
1794920199 79
1794920204 79
1794920209 79
1794920214 79
1794920219 79
1794920224 79
1794920229 79
1794920235 79
1794920240 79
1794920245 79
```
</details>

---

