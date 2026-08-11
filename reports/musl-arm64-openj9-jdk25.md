---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-11 04:47:00 EDT

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
| CPU Cores (start) | 10 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 185 |
| Sample Rate | 3.08/sec |
| Health Score | 192% |
| Threads | 13 |
| Allocations | 93 |

<details>
<summary>CPU Timeline (2 unique values: 10-30 cores)</summary>

```
1786437763 10
1786437768 10
1786437773 10
1786437778 10
1786437783 10
1786437788 10
1786437793 10
1786437798 10
1786437803 10
1786437808 10
1786437813 10
1786437818 10
1786437823 10
1786437828 10
1786437833 10
1786437838 10
1786437843 10
1786437848 10
1786437853 10
1786437858 10
```
</details>

---

