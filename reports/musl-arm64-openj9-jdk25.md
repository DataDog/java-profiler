---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-17 19:15:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 189 |
| Sample Rate | 3.15/sec |
| Health Score | 197% |
| Threads | 9 |
| Allocations | 141 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 10 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1789686626 40
1789686631 40
1789686636 40
1789686641 40
1789686646 40
1789686651 40
1789686656 40
1789686661 40
1789686666 40
1789686671 40
1789686676 40
1789686681 40
1789686686 40
1789686691 40
1789686696 40
1789686701 40
1789686706 40
1789686711 40
1789686716 40
1789686721 40
```
</details>

---

