---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-27 13:58:52 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 9 |
| Allocations | 420 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 11 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (2 unique values: 53-55 cores)</summary>

```
1793123631 53
1793123636 53
1793123641 53
1793123646 53
1793123651 55
1793123656 55
1793123661 55
1793123666 55
1793123671 55
1793123676 55
1793123681 55
1793123686 55
1793123691 55
1793123696 55
1793123701 55
1793123706 55
1793123711 55
1793123716 55
1793123721 55
1793123726 55
```
</details>

---

