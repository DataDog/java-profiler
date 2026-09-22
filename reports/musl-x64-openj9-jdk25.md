---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-22 12:28:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 427 |
| Sample Rate | 7.12/sec |
| Health Score | 445% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 11 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (2 unique values: 60-62 cores)</summary>

```
1790094042 60
1790094047 60
1790094052 60
1790094057 60
1790094062 60
1790094067 60
1790094072 60
1790094077 62
1790094082 62
1790094087 62
1790094092 62
1790094097 62
1790094102 62
1790094107 62
1790094112 62
1790094117 62
1790094122 62
1790094127 62
1790094132 62
1790094138 62
```
</details>

---

