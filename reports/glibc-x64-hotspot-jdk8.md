---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ❌ FAIL

**Date:** 2026-11-25 13:14:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 144 |
| Sample Rate | 2.40/sec |
| Health Score | 150% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 1 |
| Sample Rate | 0.02/sec |
| Health Score | 1% |
| Threads | 1 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1795630088 96
1795630093 96
1795630098 96
1795630103 96
1795630108 96
1795630113 96
1795630118 96
1795630123 96
1795630128 96
1795630133 96
1795630138 96
1795630143 96
1795630148 96
1795630153 96
1795630158 96
1795630163 96
1795630168 96
1795630173 96
1795630178 96
1795630183 96
```
</details>

---

