---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-23 04:42:48 EST

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 11 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (4 unique values: 50-69 cores)</summary>

```
1795426643 52
1795426648 50
1795426653 50
1795426658 50
1795426663 67
1795426668 67
1795426673 69
1795426678 69
1795426683 69
1795426688 69
1795426693 69
1795426698 69
1795426703 69
1795426708 69
1795426713 69
1795426718 69
1795426723 69
1795426728 69
1795426733 69
1795426738 69
```
</details>

---

