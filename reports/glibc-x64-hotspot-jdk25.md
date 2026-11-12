---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 11:57:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 9 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 9 |
| Allocations | 42 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 5 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (4 unique values: 9-32 cores)</summary>

```
1794502136 9
1794502141 9
1794502146 9
1794502151 9
1794502156 9
1794502161 9
1794502166 11
1794502171 11
1794502176 11
1794502181 11
1794502186 11
1794502191 11
1794502196 11
1794502201 11
1794502206 11
1794502211 11
1794502216 11
1794502221 11
1794502226 11
1794502231 11
```
</details>

---

