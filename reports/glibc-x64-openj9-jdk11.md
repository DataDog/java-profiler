---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 11:54:32 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 747 |
| Sample Rate | 12.45/sec |
| Health Score | 778% |
| Threads | 9 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (5 unique values: 83-91 cores)</summary>

```
1793638106 87
1793638111 87
1793638117 87
1793638122 87
1793638127 87
1793638132 87
1793638137 87
1793638142 87
1793638147 89
1793638152 89
1793638157 89
1793638162 85
1793638167 85
1793638172 83
1793638177 83
1793638182 89
1793638187 89
1793638192 89
1793638197 91
1793638202 91
```
</details>

---

