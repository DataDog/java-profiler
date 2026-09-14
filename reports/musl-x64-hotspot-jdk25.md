---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-14 12:04:49 EDT

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 729 |
| Sample Rate | 12.15/sec |
| Health Score | 759% |
| Threads | 11 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (5 unique values: 82-96 cores)</summary>

```
1789401550 82
1789401555 82
1789401560 88
1789401565 88
1789401570 88
1789401575 88
1789401580 88
1789401585 88
1789401590 88
1789401595 92
1789401600 92
1789401605 92
1789401610 92
1789401615 92
1789401620 94
1789401625 94
1789401630 94
1789401635 94
1789401640 94
1789401645 94
```
</details>

---

