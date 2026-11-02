---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-02 11:54:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 443 |
| Sample Rate | 7.38/sec |
| Health Score | 461% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 664 |
| Sample Rate | 11.07/sec |
| Health Score | 692% |
| Threads | 10 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (5 unique values: 66-72 cores)</summary>

```
1793638112 72
1793638117 70
1793638122 70
1793638127 70
1793638132 70
1793638137 68
1793638142 68
1793638147 68
1793638153 66
1793638158 66
1793638163 68
1793638168 68
1793638173 68
1793638178 68
1793638183 68
1793638188 68
1793638193 68
1793638198 68
1793638203 71
1793638208 71
```
</details>

---

