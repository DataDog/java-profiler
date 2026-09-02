---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-02 09:19:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 771 |
| Sample Rate | 12.85/sec |
| Health Score | 803% |
| Threads | 11 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (3 unique values: 60-76 cores)</summary>

```
1788354657 76
1788354662 76
1788354667 76
1788354672 76
1788354677 76
1788354682 76
1788354687 76
1788354692 68
1788354697 68
1788354702 60
1788354707 60
1788354712 60
1788354717 60
1788354722 60
1788354727 60
1788354732 60
1788354737 60
1788354742 60
1788354747 60
1788354752 60
```
</details>

---

