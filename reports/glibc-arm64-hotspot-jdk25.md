---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-02 11:02:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 155 |
| Sample Rate | 2.58/sec |
| Health Score | 161% |
| Threads | 10 |
| Allocations | 104 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 176 |
| Sample Rate | 2.93/sec |
| Health Score | 183% |
| Threads | 11 |
| Allocations | 143 |

<details>
<summary>CPU Timeline (3 unique values: 36-40 cores)</summary>

```
1793635056 36
1793635061 36
1793635066 36
1793635071 36
1793635076 36
1793635081 36
1793635086 36
1793635091 36
1793635096 36
1793635101 38
1793635106 38
1793635111 38
1793635116 38
1793635121 38
1793635126 38
1793635131 38
1793635136 38
1793635142 38
1793635147 38
1793635152 38
```
</details>

---

