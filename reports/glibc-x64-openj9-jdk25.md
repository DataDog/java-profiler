---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-11 14:07:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 506 |
| Sample Rate | 8.43/sec |
| Health Score | 527% |
| Threads | 11 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 12 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (3 unique values: 81-86 cores)</summary>

```
1773252142 82
1773252147 82
1773252152 82
1773252157 82
1773252162 82
1773252167 82
1773252172 82
1773252177 82
1773252182 86
1773252187 86
1773252192 86
1773252197 86
1773252202 86
1773252207 86
1773252212 86
1773252217 86
1773252222 86
1773252227 86
1773252232 86
1773252237 86
```
</details>

---

