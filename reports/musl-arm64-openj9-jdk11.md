---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-05 09:37:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 668 |
| Sample Rate | 11.13/sec |
| Health Score | 696% |
| Threads | 9 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (3 unique values: 41-48 cores)</summary>

```
1793889106 48
1793889111 48
1793889116 48
1793889121 48
1793889126 48
1793889131 48
1793889136 48
1793889141 48
1793889146 48
1793889151 48
1793889156 48
1793889161 48
1793889166 48
1793889171 48
1793889176 43
1793889181 43
1793889186 41
1793889191 41
1793889196 41
1793889201 41
```
</details>

---

