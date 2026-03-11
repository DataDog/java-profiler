---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-03-11 14:07:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 993 |
| Sample Rate | 16.55/sec |
| Health Score | 1034% |
| Threads | 10 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
1773252117 64
1773252122 64
1773252127 64
1773252132 64
1773252137 64
1773252142 64
1773252147 64
1773252152 64
1773252157 60
1773252162 60
1773252167 60
1773252172 60
1773252177 60
1773252182 60
1773252187 60
1773252192 60
1773252197 60
1773252202 60
1773252207 60
1773252212 60
```
</details>

---

