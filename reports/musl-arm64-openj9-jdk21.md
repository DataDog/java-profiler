---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-02 05:56:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 12 |
| Allocations | 45 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 10 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (3 unique values: 33-36 cores)</summary>

```
1793616704 36
1793616709 36
1793616714 36
1793616719 36
1793616724 36
1793616729 36
1793616734 36
1793616739 36
1793616744 36
1793616749 36
1793616754 36
1793616759 36
1793616764 36
1793616769 36
1793616774 34
1793616779 34
1793616784 34
1793616789 34
1793616794 34
1793616799 34
```
</details>

---

