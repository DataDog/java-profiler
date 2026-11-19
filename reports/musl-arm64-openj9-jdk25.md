---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-19 13:30:05 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 12 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795112639 50
1795112644 50
1795112649 50
1795112654 50
1795112659 50
1795112664 50
1795112669 50
1795112674 50
1795112679 50
1795112684 50
1795112689 50
1795112694 50
1795112699 50
1795112704 50
1795112709 50
1795112714 50
1795112719 50
1795112724 50
1795112729 50
1795112734 50
```
</details>

---

