---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-02 11:54:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 451 |
| Sample Rate | 7.52/sec |
| Health Score | 470% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 604 |
| Sample Rate | 10.07/sec |
| Health Score | 629% |
| Threads | 11 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (4 unique values: 72-77 cores)</summary>

```
1793638057 74
1793638062 74
1793638067 74
1793638072 74
1793638077 74
1793638082 74
1793638087 74
1793638092 76
1793638097 76
1793638102 72
1793638107 72
1793638112 72
1793638117 72
1793638122 72
1793638127 72
1793638132 72
1793638137 72
1793638142 77
1793638147 77
1793638152 77
```
</details>

---

