---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-21 12:26:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 898 |
| Sample Rate | 14.97/sec |
| Health Score | 936% |
| Threads | 10 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (3 unique values: 69-73 cores)</summary>

```
1792599621 69
1792599626 69
1792599631 69
1792599636 69
1792599641 71
1792599646 71
1792599651 73
1792599656 73
1792599661 73
1792599666 73
1792599671 73
1792599676 73
1792599681 73
1792599686 71
1792599691 71
1792599696 71
1792599701 71
1792599706 71
1792599711 71
1792599716 71
```
</details>

---

