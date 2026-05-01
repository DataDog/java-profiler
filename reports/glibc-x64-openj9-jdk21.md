---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-01 16:11:18 EDT

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 9 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 657 |
| Sample Rate | 10.95/sec |
| Health Score | 684% |
| Threads | 11 |
| Allocations | 420 |

<details>
<summary>CPU Timeline (2 unique values: 77-82 cores)</summary>

```
1777666101 77
1777666106 77
1777666111 77
1777666116 82
1777666121 82
1777666126 82
1777666131 82
1777666136 82
1777666141 82
1777666146 82
1777666151 82
1777666156 82
1777666161 82
1777666166 82
1777666171 82
1777666176 82
1777666181 82
1777666186 82
1777666191 82
1777666196 82
```
</details>

---

